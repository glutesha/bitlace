<script lang="ts">
    import Preview from "./Preview.svelte";
    import { pics, fetchSaves } from "../saves";
    import { onMount } from "svelte";
    import Delete from "./Delete.svelte";
  

    onMount(async () => {
        await fetchSaves();
    })
</script>

<div class="bg-neutral-900 rounded-2xl mt-3 mb-2 overflow-hidden flex flex-col w-full min-h-95 shadow-xl shadow-black/50 max-w-[380px]">
  <Delete />
  <div class="flex justify-center gap-2 flex-wrap p-4">
    {#each $pics as pic, id}
      <Preview id={id} display={pic} />
    {/each}
  </div>
</div>