<script lang="ts">
    import Preview from "./Preview.svelte";
    import { pics, fetchSaves } from "../saves";
    import { onMount } from "svelte";
    import Delete from "./Delete.svelte";
    import Export from "./Export.svelte";
    import Import from "./Import.svelte";

    onMount(async () => {
        await fetchSaves();
    })
</script>

<div class="bg-neutral-900 rounded-2xl mt-3 mb-2 overflow-hidden flex flex-col w-full shadow-xl shadow-black/50 max-w-[380px] items-center justify-center">
  <Delete />
  <div class="flex justify-center gap-2 flex-wrap p-4">
    {#if $pics.length === 0}
      <p class="text-2xl text-neutral-500 text-center">Empty! I suggest you add something cool here ;3</p>
    {:else}
      {#each $pics as pic, id}
        <Preview id={id} display={pic} />
      {/each}
    {/if}
  </div>
  <div class="flex flex-row items-center justify-center gap-2 p-2 bg-neutral-600 w-full">
    <Export />
    <Import />
  </div>
</div>