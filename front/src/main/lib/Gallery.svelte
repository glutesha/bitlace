<script lang="ts">
    import Preview from "./Preview.svelte";
    import { pics, fetchSaves } from "../saves";
    import { onMount } from "svelte";


    onMount(async () => {
        await fetchSaves();
    })

</script>
<div class="bg-neutral-900 rounded-2xl p-5 flex flex-wrap gap-2 ">
  {#if $pics}
    {#each Object.entries($pics) as [id, data]}
      <Preview id={Number(id)} display={data} />
    {/each}
  {/if}
</div>